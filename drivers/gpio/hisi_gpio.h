#include <linux/hwspinlock.h>
#include <linux/gpio.h>
#include <linux/spinlock.h>
#include <linux/workqueue.h>
#include <linux/of_address.h>
#include <linux/version.h>

#define GPIODATA 0x3fc
#define	GPIO_HWLOCK_ID	1
#define	LOCK_TIMEOUT	1000
#ifdef CONFIG_PM

struct pl061_context_save_regs {
	u8 gpio_data;
	u8 gpio_dir;
	u8 gpio_is;
	u8 gpio_ibe;
	u8 gpio_iev;
	u8 gpio_ie;
};
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,14,0))
struct pl061 {
	raw_spinlock_t	lock;
	int		sec_status;
	void __iomem	*base;
	struct gpio_chip	gc;
	int                     parent_irq;
	bool		uses_pinctrl;
#ifdef CONFIG_PM
	struct pl061_context_save_regs csave_regs;
#endif
	struct amba_device *adev;
};

int pl061_check_security_status(struct pl061 *chip);
#else
struct pl061_gpio {
	spinlock_t	lock;
	int		sec_status;
	void __iomem	*base;
	struct gpio_chip	gc;
	bool		uses_pinctrl;
#ifdef CONFIG_PM
	struct pl061_context_save_regs csave_regs;
#endif
	struct amba_device *adev;
};

int pl061_check_security_status(struct pl061_gpio *chip);
#endif
int pl061_parse_gpio_base(struct device *dev);
