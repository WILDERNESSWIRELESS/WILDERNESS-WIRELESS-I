print ("---------------------")
print("Setting up timer")
tmr.alarm(0, 3*1000, tmr.ALARM_AUTO, function()

    local led_pin = 3
    local in_pin = 1
    local result = 0
    --[[]
    gpio.mode(led_pin, gpio.OUTPUT)
    gpio.mode(in_pin, gpio.INPUT, pullup)
    print("Reading pin state...")
    result = gpio.read(in_pin)
    print(result)
    if result then
        gpio.write(led_pin, gpio.LOW)
    else
        gpio.write(led_pin, gpio.HIGH)
    end
    ]]--
    gpio.write(led_pin, gpio.LOW)
    print("In the timer function:")
end)

print("Done.")
print ("---------------------")
