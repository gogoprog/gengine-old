function init()
    gengine.application.setName("[gengine] tests")
    gengine.application.setExtent(1,1)
end

local currentTestName

function start()
    print("----------------")
    print("Running tests...")
    for k, v in pairs(_G) do
        if type(v) == "function" then
            if k:sub(1,4) == "test" then
                currentTestName = k
                v()
            end
        end
    end
    print("----------------")
    summary()
    print("----------------")
end

function update(dt)
    gengine.application.quit()
end

function stop()
end

local failed, passed = 0, 0

function summary()
    print("Passed: " .. passed .. "/" .. (passed+failed))

    if failed > 0 then
        print("Some tests failed!!")
        print("Failed: " .. failed)
    end
end

function getFailureLine(trace)
    local matches = {}
    for v in string.gmatch(trace, ":([0-9]*):") do table.insert(matches, v) end
    return matches[2]
end

function check(expected, actual)
    if expected == actual then
        passed = passed + 1
    else
        print("Error! Was " .. tostring(actual) .. " but was expecting " .. tostring(expected))
        print("In " .. currentTestName .. " at " .. getFailureLine(debug.traceback()))
        failed = failed + 1
    end
end

local epsilon = 0.0001

function checkRoughly(expected, actual)
    if expected < actual + epsilon and expected > actual - epsilon then
        passed = passed + 1
    else
        print("Error! Was " .. tostring(actual) .. " but was expecting " .. tostring(expected))
        print("In " .. currentTestName .. " at line " .. getFailureLine(debug.traceback()))
        failed = failed + 1
    end
end

-------------------------------------------------------------------------------------------------
-- TESTS
-------------------------------------------------------------------------------------------------

function testMath()
    local v1, v2 = vector2(1, 2), vector2(3, 4)
    local av, lv = v1 + v2, v1 - v2
    local mv = v1 * 3

    check(vector2(4, 6), av)
    check(vector2(-2, -2), lv)
    check(vector2(3, 6), mv)

    checkRoughly(2.828427, gengine.math.getDistance(v1, v2))
    checkRoughly(8, gengine.math.getSquareDistance(v1, v2))

    v1:set(mv)

    check(vector2(3, 6), v1)
end
