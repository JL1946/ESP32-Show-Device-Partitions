# ESP32-Show-Device-Partitions
There is a code snippet designed to print the ESP32 Device's Partitions that can be found elsewhere on GitHub.

There is a problem with the snippet in that it causes the compiler to issue a warning for both do-while loops --> do...-while (_mypartiterator = esp_partition_next(_mypartiterator));
This warning is caused because the Assignment Operator(=) should be an Is-Equal-To Operator(==). However, if corrected to remove the warning --> do...-while (_mypartiterator == esp_partition_next(_mypartiterator));
The code causes a kernel panic when _mypartiterator becomes NULL. I re-wrote the do-while loop to the following while loop:

		while (_mypartiterator != NULL)
		{
			_mypart = esp_partition_get(_mypartiterator);
			printf("Type: %02x SubType %02x Address 0x%06X Size 0x%06X Encryption %i Label %s\r\n", _mypart->type, _mypart->subtype, _mypart->address, _mypart->size, _mypart->encrypted, _mypart->label);
			_mypartiterator = esp_partition_next(_mypartiterator);
		}

The change removes the warning and the kernel panic
