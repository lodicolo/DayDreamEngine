#include "DreamCamera.h"
#include <DreamInput.h>
#include <DreamTimeManager.h>
#include "DreamGraphics.h"
#include "DreamGLFW.h"
#include <GLFW/glfw3.h>

DreamCamera::DreamCamera() : DreamGameObject()
{
	transform.position.z = 1.0f;
	transform.SetRotation(DreamMath::DreamVector3(0.0f, 180.0f, 0.0f));
	// transform.SetForward(DreamMath::DreamVector3(0.0f, 0.0f, -1.0f)); //TODO: immediately breaks
}

DreamCamera::~DreamCamera()
{
}

void DreamCamera::Update()
{
	float deltaTime = DreamTimeManager::deltaTime;
	float speed = cameraSpeed * cameraSpeedMultiplier;

	// Movement Controls
	if (glfwGetKey(window, GLFW_KEY_W))
	// if (DreamInput::KeyDown(KeyCode::W))
	{
		transform.position += (transform.GetForward() * speed) * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_A))
	// if (DreamInput::KeyDown(KeyCode::A))
	{
		transform.position += (transform.GetRight() * -speed) * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_S))
	// if (DreamInput::KeyDown(KeyCode::S))
	{
		transform.position += (transform.GetForward() * -speed) * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_D))
	// if (DreamInput::KeyDown(KeyCode::D))
	{
		transform.position += (transform.GetRight() * speed) * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE))
	// if (DreamInput::KeyDown(KeyCode::SPACE))
	{
		transform.position += (DreamVector3(0.0f, 1.0f, 0.0f) * speed) * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) | glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL))
	// if (DreamInput::KeyDown(KeyCode::CTRL))
	{
		transform.position -= (DreamVector3(0.0f, 1.0f, 0.0f) * speed) * deltaTime;
	}

	cameraSpeedMultiplier = 1.0f;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) | glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT))
	// if (DreamInput::KeyDown(KeyCode::SHIFT))
	{
		cameraSpeedMultiplier = cameraSpeedMaxMultiplier;
	}

	// FoV Controls
	if (glfwGetKey(window, GLFW_KEY_Q))
	// if (DreamInput::KeyDown(KeyCode::Q))
	{
		fieldOfView -= 30.0f * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_E))
	// if (DreamInput::KeyDown(KeyCode::E))
	{
		fieldOfView += 30.0f * deltaTime;
	}

	// Zoom Controls
	if (glfwGetKey(window, GLFW_KEY_Z))
	// if (DreamInput::KeyDown(KeyCode::Z))
	{
		zoom -= 1.0f * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_C))
	// if (DreamInput::KeyDown(KeyCode::C))
	{
		zoom += 1.0f * deltaTime;
	}

	// Cam Rotation Controls
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	// if (DreamInput::KeyPressed(KeyCode::MOUSE_LEFT_CLICK))
	{
		if (!isClicking)
		{
			wasClicking = false;
			isClicking = true;
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			mouseStartPos = {
				(float)x,
				(float)y};
			// mouseStartPos = DreamInput::GetMousePosScreen();
		}
	}
	else
	{
		wasClicking = isClicking;
		isClicking = false;
	}

	// Cam Zoom Controls
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	// if (DreamInput::KeyDown(KeyCode::MOUSE_RIGHT_CLICK))
	{
		if (instantZoom)
		{
			zoom = maxZoom;
		}
		else
		{
			if (zoom != maxZoom)
			{
				zoom += zoomSpeed * deltaTime;
				if (zoom >= maxZoom)
				{
					zoom = maxZoom;
				}
			}
		}
	}
	else
	{
		if (instantZoom)
		{
			zoom = minZoom;
		}
		else
		{
			if (zoom != minZoom)
			{
				zoom -= zoomSpeed * deltaTime;
				if (zoom <= minZoom)
				{
					zoom = minZoom;
				}
			}
		}
	}

	if (wasClicking)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		mouseCurPos = {
			(float)x,
			(float)y};
		// mouseCurPos = DreamInput::GetMousePosScreen();
		DreamMath::DreamVector2 distDragged = mouseCurPos - mouseStartPos;
		// printf("dragged %f,%f from %f,%f to %f,%f\n", distDragged.x, distDragged.y, mouseStartPos.x, mouseStartPos.y, mouseCurPos.x, mouseCurPos.y);
		mouseStartPos = mouseCurPos;

		distDragged *= cameraRotSpeed * deltaTime;
		printf("dragged %f, %f\n", distDragged.x, distDragged.y);

		transform.Rotate(DreamMath::DreamVector3(distDragged.y, -distDragged.x, 0.0f));
	}

	float aspectratio = DreamGraphics::GetAspectRatio();
	//float aspectratio = 0.1f;

	projectionMat = DreamMath::CreateProjectionMatix(fieldOfView, nearClipDist, farClipDist, aspectratio, zoom);
	viewMat = DreamMath::LookAtViewMatix(transform.position, transform.position + transform.GetForward(), transform.GetUp());

	// transform.Rotate(DreamMath::DreamVector3{0, 0, 0.01f});
	// auto forward = transform.GetForward();
	// printf("forward %f, %f, %f\n", forward.x, forward.y, forward.z);

	// Perspective matrix
	// Update our projection matrix since the window size changed
	// XMMATRIX P = XMMatrixPerspectiveFovLH(
	//	0.25f * 3.1415926535f,	// Field of View Angle
	//	(float)width / height,	// Aspect ratio
	//	0.1f,				  	// Near clip plane distance
	//	100.0f);			  	// Far clip plane distance
	// XMStoreFloat4x4(&cam->projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}
