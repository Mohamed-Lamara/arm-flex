#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <stdint.h>

void Feedback_Init(void);
void Feedback_Play(uint16_t duration_ms);
void Feedback_Update(void);

#endif
