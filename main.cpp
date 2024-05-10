#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Déclaration des paramètres de la fenêtre
const int WIDTH = 800;
const int HEIGHT = 800;

// definition du vertex shader en GL shding language (GLSL)
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// definition du fragment shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0"; 



int main() {

	// Initialisation de GLFW
	glfwInit();

	// Indiquer a GLFW la version de OpenGL utilisé
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Création de la fenêtre
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "game engine", NULL, NULL);
	
	// Détection d'erreur
	if (window == NULL) {
		std::cout << "Failed to create window" << "/n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);



	// OPENGL

	// initialiser openGL
	gladLoadGL();

	// initalise la fenetre de rafraichissement
	glViewport(0, 0, WIDTH, HEIGHT);


	// VERTEX SHADER

	// creation d'un objet shader avec son ID
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// relier le nouvel objet avec le code source et le compiler
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// verification si la compilation est reussi
	int  success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		// Recuperer le message d'erreur
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// FRAGMENT SHADER

	// Creation d'un objet shader avec son ID
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// relier le nouvel objet avec le code source et le compiler
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	// verification si la compilation est reussi
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		// Recuperer le message d'erreur
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}



	// SHADER PROGRAM

	// creer l'objet GL pour le program de shader
	GLuint shaderProgram = glCreateProgram();

	// attacher les shaders avec le program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// construire le program
	glLinkProgram(shaderProgram);

	// verification que le program link bien
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	// On enleve les anciens shader etant donne qu'on les a deja compilé et linker au program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// VERTEX INPUT

	// definition d'un triangle
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f


	};

	GLuint indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	// Vertex Array et Buffer Objects VAO, VBO

	GLuint VAO, VBO , EBO;

	// Generer un VAO et un VBO associés aux objets instanciés plus haut
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Relier le VAO au vertex array du GPU
	glBindVertexArray(VAO);

	// Relier le VBO au vertex buffer du GPU
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Lier vertices au VBO

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Boucle pour garder la fenêtre ouverte
	while (!glfwWindowShouldClose(window)) {


		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// Terminaison de la fenêtre et de GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}