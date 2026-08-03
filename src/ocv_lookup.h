typedef struct {
	float v;
	float soc;
} OCV_Table_t;

extern const OCV_Table_t ocv_table[];

#define TABLE_SIZE (sizeof(ocv_table) / sizeof(ocv_table[0]))

float ocv_lookup(float voltage);
