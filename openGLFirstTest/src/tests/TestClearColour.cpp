#include "TestClearColour.h"

#include "DebugTools.h"
#include "imgui\imgui.h"

namespace test
{
	TestClearColour::TestClearColour()
		: m_ClearColour{ 1.0f, 0.0f, 1.0f, 1.0f }
	{
	}

	TestClearColour::~TestClearColour()
	{
	}

	void TestClearColour::OnUpdate(float deltaTime)
	{
	}

	void TestClearColour::OnRender()
	{
		GLCALL(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColour::OnImGuiRender()
	{
		ImGui::Begin("Clear Colour Test");
		ImGui::ColorEdit4("Clear Colour", m_ClearColour);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}