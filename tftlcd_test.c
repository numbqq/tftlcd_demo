#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

#include <tftlcd.h>

#include "pic.h"
#include "qq.h"

static int is_running = 1;

void signal_handler(int s)
{
	is_running = 0;
}

int main(int argc, char **argv)
{
	int ret;
	struct timeval time_start, time_end;
	float total_time = 0;
	int frames = 0;

	signal(SIGINT, signal_handler);

	ret = tftlcd_open();
	if (ret) {
		printf("tftlcd_open failed, error: %d\n", ret);
	}

	ret |= tftlcd_clear(BLACK);

	ret |= tftlcd_draw_string(100, 100, RED, GREEN, FONT_SIZE_32, FONT_BACKGROUND_ON, "Hello");

	ret |= tftlcd_draw_string_simple(100, 150, BLUE, FONT_SIZE_24, "Draw String Simple");

	sleep(1);

	ret |= tftlcd_clear(WHITE);

	ret |= tftlcd_draw_picture(100, 0, 40, 40, (uint8_t *)gImage_qq);

	ret |= tftlcd_draw_string(100, 100, RED, GREEN, FONT_SIZE_32, FONT_BACKGROUND_OFF, "Hello");

	ret |= tftlcd_fill_rectangle(0, 0, 100, 200, RED);

	ret |= tftlcd_draw_picture(100, 40, TFTLCD_WIDTH, TFTLCD_HEIGHT, (uint8_t *)gImage_111);

	sleep(1);

	ret |= tftlcd_set_backlight(0);
	sleep(1);
	ret |= tftlcd_set_backlight(1);

	sleep(1);

	ret |= tftlcd_set_power(0);
	sleep(1);
	ret |= tftlcd_set_power(1);
	sleep(1);

	while (is_running)
	{

		gettimeofday(&time_start, 0);

		ret |= tftlcd_draw_picture(0, 0, TFTLCD_WIDTH, TFTLCD_HEIGHT, (uint8_t *)gImage_123);
		ret |= tftlcd_draw_picture(0, 0, TFTLCD_WIDTH, TFTLCD_HEIGHT, (uint8_t *)gImage_111);
		ret |= tftlcd_draw_picture(0, 0, TFTLCD_WIDTH, TFTLCD_HEIGHT, (uint8_t *)gImage_222);
		ret |= tftlcd_draw_picture(0, 0, TFTLCD_WIDTH, TFTLCD_HEIGHT, (uint8_t *)gImage_333);
		ret |= tftlcd_draw_picture(0, 0, TFTLCD_WIDTH, TFTLCD_HEIGHT, (uint8_t *)gImage_444);
		ret |= tftlcd_draw_picture(0, 0, TFTLCD_WIDTH, TFTLCD_HEIGHT, (uint8_t *)gImage_555);

		gettimeofday(&time_end, 0);
		total_time += (float)((time_end.tv_sec - time_start.tv_sec) + (time_end.tv_usec - time_start.tv_usec) / 1000.0f / 1000.0f);

		frames += 6;

		if (total_time >= 1.0f)
		{
			int fps = (int)(frames / total_time);
			fprintf(stderr, "FPS: %i\n", fps);

			frames = 0;
			total_time = 0;
		}
	}

	ret |= tftlcd_close();

	if (ret)
	{
		printf("Error!!!!!!!!!!!!!!!!!!!!!!\n");
		return -1;
	}


	return 0;
}
