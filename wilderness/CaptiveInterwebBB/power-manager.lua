abort = false
print('Send some xxxx Keystrokes now to abort startup.')
    -- if <CR> is pressed, abort
     uart.on("data", "x",
      function(data)
        print("receive from uart:", data)
        if data=="x" then
          abort = true
          uart.on("data")
          return
        end
    end, 0)

print ('Will launch servers in 5 seconds...')
tmr.alarm(0,5000,0,startup)

local led_pin = 3
local in_pin = 1
local result = 0
gpio.mode(led_pin, gpio.OUTPUT)
gpio.mode(in_pin, gpio.INPUT, pullup)
while 1 do
tmr.delay(1000000)
print("Reading pin state...")
result = gpio.read(in_pin)
print(result)
if not result then
gpio.write(led_pin, gpio.LOW)
else
gpio.write(led_pin, gpio.HIGH)
end
end
