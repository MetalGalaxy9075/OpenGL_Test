#include "Test.h"

namespace test {
	test::Test::Test()
	{
	}

	test::Test::~Test()
	{
	}

	void test::Test::OnUpdate(float deltaTime)
	{
	}

	void test::Test::OnRender()
	{
	}

	void test::Test::OnImGuiRender()
	{
	}

	test::TestMenu::TestMenu(Test*& currentTestPointer)
		:m_CurrentTest(currentTestPointer)
	{
	}

	void test::TestMenu::OnImGuiRender()
	{
		
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
		
	}
}