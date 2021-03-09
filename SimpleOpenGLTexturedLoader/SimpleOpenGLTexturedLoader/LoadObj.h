#pragma once

bool LoadScene(const char* path);

void RenderModelByIndex_triciclo(int index, state_type state, float);
void RenderModelByIndex_button(int index, bool isMouseOn);
void RenderModelByIndex(int index);

void ReleaseScene();
