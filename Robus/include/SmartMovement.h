#ifndef SMARTMOVEMENT_H
#define SMARTMOVEMENT_H

//void smart_movement_lock_update(void);
//bool smart_movement_init(void);
//bool smart_movement_lock(uint32_t* goal);

void smart_ir_read(uint32_t* distance);

bool smart_align_init(uint32_t distance);
void smart_align_status(uint32_t* state, bool action);
void smart_align(void);

#endif