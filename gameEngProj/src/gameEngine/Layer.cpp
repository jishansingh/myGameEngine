#pragma once
#include"Layer.h"
#include"GameWindow.h"


gameEngine::Layer::Layer(GameWindow* win) {
	window = win;
}

gameEngine::ImGUILayer::ImGUILayer(GameWindow* win) : Layer(win) {  }

void gameEngine::ImGUILayer::onAttach() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
	//io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	//io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	//io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
	//io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	//io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	//io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	//io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	//io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	//io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	//io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	//io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	//io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	//io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	//io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	//io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	//io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	//io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
	//io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	//io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	//io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	//io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	//io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	//io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	ImGui::StyleColorsDark();
	//manager->addNewObj(winCam);

	ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
}
void gameEngine::ImGUILayer::onUpdate() {
	static bool show_demo_window = true;
	static bool show_another_window = false;
	static ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
	static float m_time = glfwGetTime();

	ImGuiIO& io = ImGui::GetIO();
	int framebufferwidth;
	int framebufferheight;
	glfwGetFramebufferSize(window->getWindow(), &framebufferwidth, &framebufferheight);
	io.DisplaySize = ImVec2(framebufferwidth, framebufferheight);
	ImGui::SetNextWindowSize(io.DisplaySize);
	float time = glfwGetTime();
	io.DeltaTime = 1 / 60.f;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	ImGui::Begin("debug menu");
	for (auto som : menus) {
		som();
	}
	ImGui::End();

	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}


	ImGui::EndFrame();

}

void gameEngine::ImGUILayer::renderLayer() {

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void gameEngine::ImGUILayer::endLayer() {

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

}
