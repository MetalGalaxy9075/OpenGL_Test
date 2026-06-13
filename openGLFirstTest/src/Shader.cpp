#include "Shader.h"




Shader::Shader(const std::string& filepath) 
	:m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);


    //creates a shader and returns an id
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() 
{
    GLCALL(glDeleteProgram(m_RendererID));
}

 ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            if (type == ShaderType::VERTEX)
                ss[0] << line << '\n';
            if (type == ShaderType::FRAGMENT)
                ss[1] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };

}

 unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    //creates the shader with an id pointer
    unsigned int id = glCreateShader(type);

    //creates a char array pointer (pointer to the start of a string in memmory)
    const char* src = source.c_str();
    //tells the shader where to get a string
    glShaderSource(id, 1, &src, nullptr);
    //sets up the shader
    glCompileShader(id);

    //error handling, gets length of log, allocates bytes the length of the log and allocates a char pointer, puts the log into the allocated memmory, prints the log, deletes the shader so no errors ocour
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        //std::cout << "Shader failed to compile " << (type == GL_VERTEX_SHADER ? "vertex":"fragment")":" << std::endl;
        std::cout << "Shader failed to compile " << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    //todo: error handling

    return id;
}

 unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    //creates a program variable that holds multiple shaders
    unsigned int program = glCreateProgram();

    //gives a reverence to a shader in an unsigned int and creates the two nercassary shaders
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //adds shader to the program
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    //sets up the program
    glLinkProgram(program);
    glValidateProgram(program);

    //deletes the shaders that are now stored in the program
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}

void Shader::Bind() const 
{
    GLCALL(glUseProgram(m_RendererID));
}
void Shader::Unbind() const 
{
    GLCALL(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string name, int value) 
{
    GLCALL(glUniform1i(GetUniformLocation(name), value));
}


void Shader::SetUniform4f(const std::string name, float v0, float v1, float v2, float v3) 
{
    GLCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) 
{
    GLCALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) 
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCALL( int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning, Uniform " << name << " doesn't exist" << std::endl;
        m_UniformLocationCache[name] = location;
    return location;
}