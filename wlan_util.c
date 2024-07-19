#ifdef POWER_PERCENT_ADJUSTMENT
int txpower_percent_to_level(u8 percentage)
{
	const int percent_threshold_pos[] = {105, 118, 133, 149, 167, 188, 211};
	const int percent_threshold_neg[] = {95, 85, 75, 67, 60, 54, 48, 43, 38, 34, 30, 27, 24, 22, 19, 17, 15, 14, 12, 11, 10};
	const int pwrlevel_diff[9] = { -40, -34, -30, -28, -26, -24, -23, -22, -21}; // for < 10% case
	int i;

	if (percentage > 100) {
		for (i = 0; i < ARRAY_SIZE(percent_threshold_pos); i++) {
			if (percentage <= percent_threshold_pos[i]) {
				return i;
			}
		}
		return 6; /* +3db */
	} else if (percentage <= 100 && percentage >= 1) {
		for (i = 0; i < ARRAY_SIZE(percent_threshold_neg); i++) {
			if (percentage >= percent_threshold_neg[i]) {
				return (int) - i;
			}
		}
	} else if (percentage < 1)
		percentage = 1;

	return pwrlevel_diff[percentage - 1];
}
#endif /* POWER_PERCENT_ADJUSTMENT */
