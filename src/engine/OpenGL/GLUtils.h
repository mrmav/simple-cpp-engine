#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <iomanip>
#include <string>

// static class for checking gl errors
class GLUtils
{

public:

	static void CheckErrors()
	{
		GLenum err;
		const char* errstring;

		while ((err = glGetError()) != GL_NO_ERROR)
		{			
			std::cout << "GL ERROR: "<< err << std::endl;
		}
	};
	
	// see: https://gist.github.com/liam-middlebrook/c52b069e4be2d87a6d2f
	// Callback function for printing debug statements
	static void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
								GLenum severity, GLsizei length,
								const GLchar *msg, const void *data)
	{
		const char* _source;
		const char* _type;
		const char* _severity;

		switch (source) {
			case GL_DEBUG_SOURCE_API:
			_source = "API";
			break;

			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			_source = "WINDOW SYSTEM";
			break;

			case GL_DEBUG_SOURCE_SHADER_COMPILER:
			_source = "SHADER COMPILER";
			break;

			case GL_DEBUG_SOURCE_THIRD_PARTY:
			_source = "THIRD PARTY";
			break;

			case GL_DEBUG_SOURCE_APPLICATION:
			_source = "APPLICATION";
			break;

			case GL_DEBUG_SOURCE_OTHER:
			_source = "UNKNOWN";
			break;

			default:
			_source = "UNKNOWN";
			break;
		}

		switch (type) {
			case GL_DEBUG_TYPE_ERROR:
			_type = "ERROR";
			break;

			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			_type = "DEPRECATED BEHAVIOR";
			break;

			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			_type = "UDEFINED BEHAVIOR";
			break;

			case GL_DEBUG_TYPE_PORTABILITY:
			_type = "PORTABILITY";
			break;

			case GL_DEBUG_TYPE_PERFORMANCE:
			_type = "PERFORMANCE";
			break;

			case GL_DEBUG_TYPE_OTHER:
			_type = "OTHER";
			break;

			case GL_DEBUG_TYPE_MARKER:
			_type = "MARKER";
			break;

			default:
			_type = "UNKNOWN";
			break;
		}

		switch (severity) {
			case GL_DEBUG_SEVERITY_HIGH:
			_severity = "HIGH";
			break;

			case GL_DEBUG_SEVERITY_MEDIUM:
			_severity = "MEDIUM";
			break;

			case GL_DEBUG_SEVERITY_LOW:
			_severity = "LOW";
			break;

			case GL_DEBUG_SEVERITY_NOTIFICATION:
			_severity = "NOTIFICATION";
			break;

			default:
			_severity = "UNKNOWN";
			break;
		}

		std::ostringstream outputStream;
		outputStream << id << ": " << _type << " of " << _severity << ", raised from " << _source << ":" << "\n";
		outputStream << GLUtils::BreakString(msg, 64) << std::endl;

		std::cout << outputStream.str() << std::endl;

		/*printf("%d: %s of %s severity, raised from %s: %s\n",
				id, _type, _severity, _source, msg);*/

	}
		

private:
	
	GLUtils();  // disable the creation of an instance

	static std::string BreakString(const std::string s, int lineWidth)
	{
		std::string result = s;

		size_t strLen = result.size();

		for (int i = 0; i < strLen; i++)
		{
			if (s[i] != '\0' && i % lineWidth == 0 && i > 0)
			{
				result.insert(result.begin() + i, '\n');
			}		
		}

		return result;
	}


};
