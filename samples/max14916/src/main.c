/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>

#include <zephyr/drivers/gpio.h>                                                                                                                                                     
#include <zephyr/drivers/spi.h>

// #include <zephyr/drivers/gpio/gpio_max14916.h>
// #define SPIOP           SPI_WORD_SET(8) | SPI_TRANSFER_MSB

// Blue led
#define LED0_NODE       DT_ALIAS(led1)

// SPI
#define SPI_OP  SPI_OP_MODE_MASTER |SPI_MODE_CPOL | SPI_MODE_CPHA | SPI_WORD_SET(8) | SPI_LINES_SINGLE

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
	printf("Hello World! Starting custom app %s\n", CONFIG_BOARD_TARGET);

	// const struct device *const dev = DEVICE_DT_GET_ONE(adi_max14916_gpio);

	// if (!device_is_ready(dev)) {
	// 	printk("Sensor: Device not ready.\n");
	// 	return 0;
	// }
        // else
        //         printk("Sensor: Sensor ready.\n");

        if (!device_is_ready(led.port))
                printk("Led: Blue led not ready\n");
        else
                printk("Led: Blue led is ready\n");

        int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
        if (ret < 0)
                printk("Led: Error on blue led configuration");
        
        // while (1){
        //         ret = gpio_pin_toggle_dt(&led);
        //         if(ret < 0)
        //                 printk("Led: Blue led error\n");
        //         k_msleep(1000);
        // }

        // struct spi_dt_spec spispec = SPI_DT_SPEC_GET(DT_NODELABEL(max14916), SPIOP, 0);

        // struct spi_config sc = spispec.config;

        // printk("Slave addrs: %d\n", sc.slave);
        // printk("SPI frequency: %d\n", sc.frequency);
        // printk("SPI operating mode: %d\n", sc.operation);


        // SPI transfer test

        printk("Program: Spi init start\n\r");

        uint8_t my_buffer[4] = {0};
        uint8_t my_buffer_send[4] = {1, 2, 3, 4};
        struct spi_buf my_spi_buffer[1];
        struct spi_buf my_spi_buffer_tx[1];
        my_spi_buffer[0].buf = my_buffer;
        my_spi_buffer[0].len = 4;

        my_spi_buffer_tx[0].buf = my_buffer_send;
        my_spi_buffer_tx[0].len = 4;
        const struct spi_buf_set rx_buff = { my_spi_buffer, 1 };
        const struct spi_buf_set tx_buff = { my_spi_buffer_tx, 1 };

        const struct spi_dt_spec spi_dev =
                SPI_DT_SPEC_GET(DT_NODELABEL(test_spi_node), SPI_OP, 0);

        printk("Program: Spi read start\n\r");
        ret = spi_read_dt(&spi_dev, &rx_buff);
        if (ret) { 
                printk("Sensor: Spi_read status: %d", ret);
        }

        printk("Program: Spi write start\n\r");
        ret = spi_write_dt(&spi_dev, &tx_buff);
        if (ret) { 
                printk("Sensor: Spi_write status: %d", ret);
        }
        printk("Program: End\n\r");

	return 0;
}
