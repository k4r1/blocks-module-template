#!/usr/bin/env python

import os
import sys
import struct
import string
import argparse
import ConfigParser

BOOTLOADER_SEARCH_TAG = 0xDA7ADA7A
BOOTLOADER_CONF_TAG = 0xB10CDA7A

'''
Target conf structure :
{
	little endian unsigned long int (4) : 0xB10CDA7A
	little endian unsigned long int (4) : filesize
	little endian unsigned long int (4) : reserved
	little endian unsigned long int (4) : version
}
'''
def ini_to_blob(configfile,filesize):
	cfg = ConfigParser.ConfigParser()
	cfg.readfp(configfile)
	
	_version = int(cfg.get("module", "version"), 0)

	return "%s" % (struct.pack("<IIII", BOOTLOADER_CONF_TAG, filesize, 0, _version))

def bootloader_insert_conf(bootloader, data, output):
	# Convert as little endian
	tag = struct.pack("<I", BOOTLOADER_SEARCH_TAG);

	plaintext = bootloader.read()

	start = plaintext.rfind(tag)

	if start == -1:
		print >> sys.stderr, "Start marker not found"
        	sys.exit(1)

	output.write(plaintext)
	output.seek(start)
	output.write(data)

if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Module Bootloader Configuration')
	parser.add_argument('-c', '--config', dest='config', default=None, 
			    help="Module configuration file")
	parser.add_argument('-b', '--bootloader', dest='bootloader', default=None, 
			    help="Bootloader binary File source")
	parser.add_argument('-o', '--output', dest='output', default=None, 
			    help="Bootloader binary File to output")
	args = parser.parse_args()

	filesize = os.path.getsize(args.bootloader)

	with open(args.config) as configfile:
		data = ini_to_blob(configfile,filesize)

	with open(args.bootloader, "r") as bootloader:
		with open(args.output, "w") as output:
			bootloader_insert_conf(bootloader, data, output)

	sys.exit(0)
