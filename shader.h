#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/gl.h>

using std::string;

class Shader {
    public:
        Shader(const string &vertex, const string &fragment);
        Shader(const string &vertex, const string &fragment, const string &geometry);
        ~Shader();
        GLuint getLocation() const;
        void use() const;
    private:
        string getFile(const string &filename);
        GLuint program;
};


#endif
