#pragma once

namespace test
{
	class TestTwoObjects
	{
	public:
		TestTwoObjects();
		~TestTwoObjects();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}