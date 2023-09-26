#ifndef IRQBinder_h
#define IRQBinder_h

#include <SketchBoundLibrary.h>

#define IRQ_COUNT 2

#ifndef MAX_IRQ_BINDINGS
#define MAX_IRQ_BINDINGS 2
#endif

#define INVOKE_IRQ(irq) if (irq < IRQ_COUNT) __irq_handlers__[irq]()

Invokable<void>* __irq_bindings__[IRQ_COUNT][MAX_IRQ_BINDINGS];
byte __irq_binding_count__[IRQ_COUNT];
void (*__irq_handlers__[IRQ_COUNT])() =
{
	[]()
	{
		for (byte i = 0; i < __irq_binding_count__[0]; i++)
			__irq_bindings__[0][i]->invoke();
	},
	[]()
	{
		for (byte i = 0; i < __irq_binding_count__[1]; i++)
			__irq_bindings__[1][i]->invoke();
	}
};

int addInternalIRQBinding(byte irq, Invokable<void>* callable)
{
	if (irq >= IRQ_COUNT)
		return 1;
	if (__irq_binding_count__[irq] == MAX_IRQ_BINDINGS)
		return 2;
	__irq_bindings__[irq][__irq_binding_count__[irq]] = callable;
	__irq_binding_count__[irq]++;
	return 0;
}

int removeInternalIRQBinding(byte irq, Invokable<void>* callable)
{
	if (irq >= IRQ_COUNT)
		return 1;

	for (byte i = 0; i < __irq_binding_count__[irq]; i++)
		if (__irq_bindings__[irq][i] == callable)
		{
			for (byte iShift = 0; iShift < __irq_binding_count__[irq] - 1; iShift++)
				__irq_bindings__[irq][iShift] = __irq_bindings__[irq][iShift + 1];
			__irq_binding_count__[irq]--;
			return 0;
		}
	return 2;
}

#endif