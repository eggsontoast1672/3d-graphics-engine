#pragma once

#include <GL/glew.h>

class ShaderProgram
{
public:
    /// Construct a shader program.
    ///
    /// The vertex and fragment source are taken by pointer to const char since
    /// the OpenGL API accepts null terminated source. Using a `const std::string&`
    /// would require that a string object be constructed at some point,
    /// and using a `std::string_view` would not guarantee null termination.
    ///
    /// The shader program object does not get bound by default, so in order to
    /// use this program after construction, one must call the `use` method.
    ShaderProgram(const char* vertex_source, const char* fragment_source);

    /// Destruct the shader program.
    ~ShaderProgram();

    /// Bind this shader program object.
    void use() const;

private:
    GLuint m_id;

    /// Check for link time errors.
    void check_link_errors() const;
};
