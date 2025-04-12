#include "FBO.h"
FBO::FBO() :FBO_index(0), colorTex(0), depthTex(0), height(600), width(800), samples(1) {}

void FBO::init(int w, int h, bool multisample)
{
	this->multisample = multisample;
	glGetIntegerv(GL_MAX_COLOR_TEXTURE_SAMPLES, &samples);

	if (this->FBO_index == 0)
		glGenFramebuffers(1, &this->FBO_index);
	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO_index);

	if (this->colorTex != 0)
		glDeleteTextures(1, &this->colorTex);
	if (this->depthTex != 0)
		glDeleteTextures(1, &this->depthTex);

	int textureOption = (multisample) ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	glGenTextures(1, &this->colorTex);
	glGenTextures(1, &this->depthTex);

	glBindTexture(textureOption, this->colorTex);
	if (multisample)
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA8, w, h, false);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureOption, this->colorTex, 0);

	glBindTexture(textureOption, this->depthTex);
	if (multisample)
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_DEPTH_COMPONENT24, w, h, false);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureOption, this->depthTex, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("FBO creation failed.\n");
		glDeleteTextures(1, &this->depthTex);
		glDeleteTextures(1, &this->colorTex);
		glDeleteFramebuffers(1, &this->FBO_index);
		return;
	}
	printf("FBO created - ID %d.\n", this->FBO_index);
	this->width = w;
	this->height = h;
}

void FBO::resolveToFbo(FBO& fbo)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->FBO_index);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo.FBO_index);
	glBlitFramebuffer(0, 0, this->width, this->height, 0, 0, this->width, this->height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void FBO::bindColorTexture(GLenum texUnit)
{
	glActiveTexture(texUnit);
	glBindTexture(GL_TEXTURE_2D, this->colorTex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
void FBO::bindDepthTexture(GLenum texUnit)
{
	glActiveTexture(texUnit);
	glBindTexture(GL_TEXTURE_2D, this->depthTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void FBO::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO_index);
	glViewport(0, 0, this->width, this->height);
}
void FBO::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool FBO::isMultisample()
{
	return this->multisample;
}
