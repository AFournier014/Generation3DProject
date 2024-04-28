#pragma once

/**
* @brief ShaderInfo structure
*
* Cette structure permet de stocker les informations relatives à un shader.
*
* @param type Type de shader (GL_VERTEX_SHADER ou GL_FRAGMENT_SHADER)
* @param filename Chemin du fichier contenant le shader
* @param shaderId Identifiant du shader
*/
struct ShaderInfo {
	unsigned int type;
	const char* filename;
	unsigned int shaderId;
};

/**
* @brief Shader class
*
* Cette classe permet de charger des shaders OpenGL.
*
*/
struct Shader
{
	static unsigned int LoadShaders(ShaderInfo* shaders);


private:
};