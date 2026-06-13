#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "tests\TestClearColour.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui\imgui_impl_opengl3.h"
#include "imgui\imgui_impl_glfw.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 540, "OpenGL Cherno Tutorial", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW failed to start" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		

		
		/* Loop until the user closes the window */

		Renderer renderer;

		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<test::TestClearColour>("Clear Color");

		

		while (!glfwWindowShouldClose(window))
		{
			GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest) 
			{
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
				ImGui::Begin("Test Menu");
				if (currentTest != testMenu && ImGui::Button("<---"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}

			/* Render here */
			

			

			ImGui_ImplOpenGL3_NewFrame();

			

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			//swaps the buffers so the gpu can render the information and we can edit the just rendered buffer
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		//deletes the program containing the two shaders (memmory cleanup)
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}

/*
*		float positions[] = {
			  -50.0f, -50.0f,  0.0f, 0.0f, //0
			   50.0f, -50.0f,  1.0f, 0.0f, //1
			   50.0f,  50.0f,  1.0f, 1.0f, //2
			  -50.0f,  50.0f,  0.0f, 1.0f  //3
		};

		unsigned int indices[] =
		{
			0,1,2,
			2,3,0
		};

		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VertexArray va;
		VertexBuffer vb(positions, 6 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.push<float>(2);
		layout.push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		

		Shader shader("res/shaders/basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);

		Texture texture("res/textures/stoneTexture.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

		Renderer renderer;
*			
			glm::vec3 translationA(200, 200, 0);
			glm::vec3 translationB(400, 200, 0);

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
				glm::mat4 mvp = proj * veiw * model;
				shader.Bind();
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(va, ib, shader);
			}
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
				glm::mat4 mvp = proj * veiw * model;
				shader.Bind();
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(va, ib, shader);
			}
			{
				ImGui::Begin("Variable Testing");
				ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 700.1f);
				ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 700.1f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
			}*/