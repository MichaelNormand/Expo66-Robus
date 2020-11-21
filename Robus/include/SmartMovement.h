#ifndef SMARTMOVEMENT_H
#define SMARTMOVEMENT_H

void smart_movement_update(void);
bool smart_movement_init(void);
bool smart_movement_lock(uint32_t* goal);

#endif