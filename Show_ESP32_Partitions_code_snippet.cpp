void getPartionTableInfo()
{
	// Get Partitionsizes
	size_t ul;
	esp_partition_iterator_t _mypartiterator;
	const esp_partition_t *_mypart;
	ul = spi_flash_get_chip_size();
	Serial.print("Flash chip size: ");
	Serial.println(ul);
	Serial.println("Partition table:");
	_mypartiterator = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_ANY, NULL);
	if (_mypartiterator)
	{
		Serial.println("App Partition table:");
		do
		{
			_mypart = esp_partition_get(_mypartiterator);
			printf("Type: %02x SubType %02x Address 0x%06X Size 0x%06X Encryption %i Label %s\r\n", _mypart->type, _mypart->subtype, _mypart->address, _mypart->size, _mypart->encrypted, _mypart->label);
		} while (_mypartiterator = (esp_partition_next(_mypartiterator)));
	}
	esp_partition_iterator_release(_mypartiterator);
	_mypartiterator = esp_partition_find(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, NULL);
	if (_mypartiterator)
	{
		Serial.println("Data Partition table:");
		do
		{
			_mypart = esp_partition_get(_mypartiterator);
			printf("Type: %02x SubType %02x Address 0x%06X Size 0x%06X Encryption %i Label %s\r\n", _mypart->type, _mypart->subtype, _mypart->address, _mypart->size, _mypart->encrypted, _mypart->label);
		} while (_mypartiterator = (esp_partition_next(_mypartiterator)));
	}
	esp_partition_iterator_release(_mypartiterator);
}


The above snippet causes the compiler to issue a warning for both do-while loops --> do...-while (_mypartiterator = esp_partition_next(_mypartiterator));
This warning is caused because the Assignment Operator(=) should be an Is-Equal-To Operator(==). However, if corrected to remove the warning --> do...-while (_mypartiterator == esp_partition_next(_mypartiterator));
The code causes a kernel panic when _mypartiterator becomes NULL. I re-wrote the do-while loop to the following while loop:

		while (_mypartiterator != NULL)
		{
			_mypart = esp_partition_get(_mypartiterator);
			printf("Type: %02x SubType %02x Address 0x%06X Size 0x%06X Encryption %i Label %s\r\n", _mypart->type, _mypart->subtype, _mypart->address, _mypart->size, _mypart->encrypted, _mypart->label);
			_mypartiterator = esp_partition_next(_mypartiterator);
		}

This change removes the warning and the kernel panic.
