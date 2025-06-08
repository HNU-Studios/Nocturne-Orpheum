#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shaders.h>
#include <iostream>
#include <vector>
#include <cmath>
void framebufferSizeCallback(GLFWwindow* win, int w, int h) { // Scales the window based on the size of the app
	glViewport(0, 0, w, h);
}
void processInput(GLFWwindow* win) { // Regitsers button press
   	 if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(win, true); // Closes window when escape pressed
    	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) { // Changes background to pink & fills shapes when W pressed
        	glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Sets window color
		glClear(GL_COLOR_BUFFER_BIT); // Displays window color
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Sets polygon to wireframe (why not)
	}
}
void makeShape(unsigned int* VAO, unsigned int* VBO, float* verts, size_t size) {	
	glGenVertexArrays(1, VAO); // Makes VAO a proper vertex array
	glGenBuffers(1, VBO); // Makes VBO a proper buffer
	glBindVertexArray(*VAO); // Binds VAO to program
	glBindBuffer(GL_ARRAY_BUFFER, *VBO); // Binds VBO to program
	glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW); // Sets the vertex data for VBO (The buffer)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Tells the VAO how to interpret verticies in order
	glEnableVertexAttribArray(0); // Turns on VAO (I think?)
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Binds buffer with new info to program
	glBindVertexArray(0); // Binds VAO with new info to program
}
// struct Sprite {
//	glm::vec2 pos;
//	glm::vec2 scale;
//	float rotation;
//	glm::vec4 color;
// };
int main() {
	glfwInit(); // Initialize GLFW
	GLFWwindow* window = glfwCreateWindow(800, 800, "App", NULL, NULL); // Makes GLFW window
	if (window == NULL) { // Makes sure window was made
        	std::cout << "Failed to create window";
        	glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Tells GLFW what the main frame is (window)
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback); // Resizes window if app scaled
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // Check GLAD status
		std::cout << "Couldn't init glad\n"; // Makes sure GLAD was initialized
		return -1; 
	}
	glViewport(0, 0, 800, 800); // Sets GLAD viewport to the window
	int success;
	char infoLog[512];
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // Checking vertex shader
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Failed vShader\n" << infoLog << "\n";
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); // Checking fragment shader
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Failed fShader\n" << infoLog << "\n";
	}
    	unsigned int shaderProgram = glCreateProgram(); // Makes shader program
    	glAttachShader(shaderProgram, vertexShader); // Link vertex shader to shader program
    	glAttachShader(shaderProgram, fragmentShader); // Link fragment shader to shader program
    	glLinkProgram(shaderProgram); // Links shaderProgram
    	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); // Checks if shaderProgram works
    	if (!success) {
		glGetProgramInfoLog(shaderProgram,512, NULL, infoLog);
	    	std::cout << "Shader program failed\n" << infoLog << "\n";
    	}
    	glDeleteShader(vertexShader); // Don't need vertex nor fragment shader anymore since now linked
    	glDeleteShader(fragmentShader);
	unsigned int vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(vertexShader2);
	glCompileShader(fragmentShader2);
	glGetShaderiv(vertexShader2, GL_COMPILE_STATUS, &success); // Checking vertex shader
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Failed vShader2\n" << infoLog << "\n";
	}
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success); // Checking fragment shader
	if (!success) {
		glGetShaderInfoLog(vertexShader2, 512, NULL, infoLog);
		std::cout << "Failed fShader2\n" << infoLog << "\n";
	}
    	unsigned int shaderProgram2 = glCreateProgram(); // Makes shader program
    	glAttachShader(shaderProgram2, vertexShader2); // Link vertex shader to shader program
    	glAttachShader(shaderProgram2, fragmentShader2); // Link fragment shader to shader program
    	glLinkProgram(shaderProgram2); // Links shaderProgram
    	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success); // Checks if shaderProgram works
    	if (!success) {
		glGetProgramInfoLog(shaderProgram,512, NULL, infoLog);
	    	std::cout << "Shader program 2 failed\n" << infoLog << "\n";
    	}
    	glDeleteShader(vertexShader2); // Don't need vertex nor fragment shader anymore since now linked
    	glDeleteShader(fragmentShader2);
	float verts[] = { // set verticies
	// Triangle one (base left)
		-0.1f, -0.3f, 0.0f,
		-0.1f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
	};
	float verts2[] = {
		// Triangle 2 (base right)
		-0.1f, -0.3f, 0.0f,
		0.0f, -0.3f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	float verts3[] = {
		// Triangle 3 (top top)
		0.0f, 0.5f, 0.0f,
		0.0f, 0.4f, 0.0f,
		0.3f, 0.5f, 0.0f
	};
	float verts4[] = {
		// Triangle 4 (top bottom)
		0.0f, 0.4f, 0.0f,
		0.3f, 0.4f, 0.0f,
		0.3f, 0.5f, 0.0f
	};
	float verts5[] = {
		// Triangle 5 (bottom top)
		0.0f, 0.2f, 0.0f,
		0.0f, 0.3f, 0.0f,
		0.25f, 0.3f, 0.0f
	};
	float verts6[] = {
		// Triangle 6 (bottom bottom)
		0.0f, 0.2f, 0.0f,
		0.25f, 0.2f, 0.0f,
		0.25f, 0.3f, 0.0f
	};
	// float verts[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.5f, 0.5f, 0.0f,

	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, 0.5f, 0.0f,
	//	-0,5f, 0.5f, 0.0f;
	// };
	//std::vector<Sprite> sprites = {
	//	{{-0.2f, 0.1f
	unsigned int VAO, VBO;
	makeShape(&VAO, &VBO, verts, sizeof(verts));
	unsigned int VAO2, VBO2;
	makeShape(&VAO2, &VBO2, verts2, sizeof(verts2));
	unsigned int VAO3, VBO3;
	makeShape(&VAO3, &VBO3, verts3, sizeof(verts3));
	unsigned int VAO4, VBO4;
	makeShape(&VAO4, &VBO4, verts4, sizeof(verts4));
	unsigned int VAO5, VBO5;
	makeShape(&VAO5, &VBO5, verts5, sizeof(verts5));
	unsigned int VAO6, VBO6;
	makeShape(&VAO6, &VBO6, verts6, sizeof(verts6));
	while (!glfwWindowShouldClose(window)) { // Main loop
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Sets to fill mode (default)
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Sets color
						      //
		processInput(window); // Calls processInput function (defined before main)
		glClear(GL_COLOR_BUFFER_BIT); // Colors window
		glUseProgram(shaderProgram); // Tells program what shaders to use
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		float redValue = cos(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, redValue, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO); // Binds the VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(VAO3); // Binds the VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(VAO5); // Binds the VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3); // Draws from current bind, shaders, VBO and VAO are binded, so uses those
		glBindVertexArray(VAO4); // Binds the VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(VAO6); // Binds the VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window); // Swap buffers
		glfwPollEvents(); // Checks IO events (keyboard, mouse, etc)
    	}
	// Deallocation of everything and killing program
	glDeleteVertexArrays(1, &VAO); 
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteProgram(shaderProgram);
    	glfwTerminate();
    	return 0;
}
