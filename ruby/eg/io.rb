require '../ev3'

#Ev3.brick_addr = '192.168.1.1'
if Ev3.ev3_init < 1
	puts "No brick"
else
	puts "OK"
end

Ev3.ev3_uninit
