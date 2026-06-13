#include "TestTwoObjects.h"

namespace test
{
	TestTwoObjects::TestTwoObjects()
	{
	}
	TestTwoObjects::~TestTwoObjects()
	{
	}
	void TestTwoObjects::OnUpdate(float deltaTime)
	{
	}
	void TestTwoObjects::OnRender()
	{
	}

	void TestTwoObjects::OnImGuiRender()
	{
		ImGui::Begin("Two objects test");
		ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 700.1f);
		ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 700.1f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}