#pragma once
#include<string>
#include"glew.h"
#include"Math.h"
class Shader {
public:
	Shader();
	~Shader();
	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	void SetActive();
	GLuint GetShaderProgram() { return mShaderProgram; }
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
private:
	bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
	bool IsCompiled(GLuint Shader);
	bool IsValidProgram();
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};