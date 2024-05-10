#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}


Shader::Shader(const char* vertexFile, const char* fragmentFile) {

	std::string vertexCode		= get_file_contents(vertexFile);
	std::string fragmentCode	= get_file_contents(fragmentFile);

	const char* vertexSource	= vertexCode.c_str();
	const char* fragmentSource	= fragmentCode.c_str();

	// VERTEX SHADER

	// creation d'un objet shader avec son ID
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// relier le nouvel objet avec le code source et le compiler
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
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
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
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
	ID = glCreateProgram();

	// attacher les shaders avec le program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// construire le program
	glLinkProgram(ID);

	// verification que le program link bien
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	// On enleve les anciens shader etant donne qu'on les a deja compilé et linker au program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}


void Shader::Activate() {

	glUseProgram(ID);

}

void Shader::Delete() {

	glDeleteProgram(ID);

}