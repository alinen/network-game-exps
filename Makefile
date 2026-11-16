all : server client
% :: %.c
	gcc  $< -o $@

