/*
 * Copyright (C) 2010 Amarula Solutions.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kallsyms.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/pm.h>
#include <linux/regulator/consumer.h>

struct personal_station {
	int	n0_general_som_to_pos_61;
};


struct regulator * v3v3_supply;


static int personal_station_request_export(struct device *dev, int flags)
{
	struct device_node *np = dev->of_node;
	int ret;
	u32 tmp;
	u8 num_relays, i;
	u32 pin_num, pin_init_val, pin_stat;
	const char *oh_name;

	if (!of_get_property(np, "pin_numbers", &tmp))
		goto error_parse;
	if (!of_get_property(np, "pin_names", &tmp))
		goto error_parse;
	if (!of_get_property(np, "pin_states", &tmp))
		goto error_parse;
	if (!of_get_property(np, "pin_init_val", &tmp))
		goto error_parse;
	num_relays = tmp / (sizeof(u32));
	dev_info(dev, "num_relays %d\n", num_relays);
	for (i = 0; i < num_relays; i++) {
		if (of_property_read_u32_index(np, "pin_numbers", i, &pin_num))
			goto error_parse;
		if (of_property_read_u32_index(np, "pin_init_val", i, &pin_init_val))
			goto error_parse;
		if (of_property_read_u32_index(np, "pin_states", i, &pin_stat))
			goto error_parse;
		if (of_property_read_string_index(np, "pin_names", i, &oh_name))
			goto error_parse;
		ret = devm_gpio_request_one(dev, pin_num, pin_stat, oh_name);
		if (ret) {
			dev_err(dev, "Failed to request GPIO %d, error %d\n",
				pin_num, ret);
			return ret;
		}
		gpio_export(pin_num, 1);
		gpio_export_link(dev, oh_name, pin_num);
	}
	return 0;

error_parse: 
	dev_err(dev, "Failed to parse DT\n");
	return -EINVAL;
}

static int personal_station_probe(struct platform_device *pdev)
{
	struct personal_station *priv;
	int ret;

	if (!pdev->dev.of_node) {
		dev_err(&pdev->dev, "This driver support only DT init\n");
		return -EINVAL;
	}
	priv = devm_kzalloc(&pdev->dev,
			sizeof(struct personal_station), GFP_KERNEL);
	if (!priv) {
		dev_err(&pdev->dev, "Failed to allocate memory\n");
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, priv);
	ret = personal_station_request_export(&pdev->dev, GPIOF_OUT_INIT_LOW);
	dev_info(&pdev->dev, "Probed\n");

	return 0;
}

static int personal_station_remove(struct platform_device *pdev)
{
	platform_set_drvdata(pdev, NULL);

	return 0;
}

static const struct of_device_id personal_station_match[] = {
	{ .compatible = "personal,personal_station-pm", },
	{ },
};

static struct platform_driver personal_station_driver = {
	.probe		= personal_station_probe,
	.remove		= personal_station_remove,
	.driver		= {
		.name	= "personal_station-pm",
		.of_match_table = of_match_ptr(personal_station_match),
	},
};

static int __init personal_station_init(void)
{
	return platform_driver_register(&personal_station_driver);
}

static void __exit personal_station_exit(void)
{
	platform_driver_unregister(&personal_station_driver);
}

module_init(personal_station_init);
module_exit(personal_station_exit);

MODULE_ALIAS("platform:personal_station-pm");
MODULE_DESCRIPTION("Personal Station Board Driver");
MODULE_LICENSE("GPL");
