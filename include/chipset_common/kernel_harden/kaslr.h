#ifndef KASLR_H
#define KASLR_H

extern unsigned int kstack_offset;
extern void kstack_randomize_init(void);

extern unsigned long kti_offset;
extern void kti_randomize_init(void);
extern void set_init_thread_info(unsigned long addr);

extern void __init set_init_stack_nx(struct thread_info *ti);
extern void set_task_stack_nx(struct thread_info *ti);

extern void __init set_init_stack_nx(struct thread_info *ti);

extern unsigned long get_module_load_offset(void);

#endif
