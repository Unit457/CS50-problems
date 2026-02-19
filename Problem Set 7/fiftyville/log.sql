-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Know more about the crime scene
SELECT *
FROM crime_scene_reports
WHERE month = 7
AND day = 28
AND year = 2024
AND street = 'Humphrey Street';
-- Time of crime: 10:15 AM
-- Place: Bakery
-- Three witnesses interviewed on 7/28/2024
-- On the same day, littering at 16:36. (seems irrelevant)

-- Check the mentioned interviews
SELECT id, name, transcript
FROM interviews
WHERE month = 7 AND day = 28 AND year = 2024;
-- Ruth: Thief left the bakery's parking lot between 10:15 and 10:25 (check bakery_security_logs)
-- Eugene: Recognizes the thief. Earlier this morning, thief withdrawals on Leggett Street (check atm_transactions)
-- Raymond: As the thief left, called someone for less than a minute. "Someone" bought him the earliest flight ticket for 7/29/2024 (check phone_calls, airports, flights)

-- Check the bakery security logs
SELECT *
FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND year = 2024
AND hour = 10 AND minute > 15 AND minute < 25;
-- There were many (8)

-- Check the atm_transactions
SELECT *
FROM atm_transactions
WHERE year = 2024 AND month = 7 AND day = 28
AND atm_location LIKE '%Leggett Street%'
AND transaction_type = 'withdraw';
-- There were many (8)

-- Check for calls
SELECT *
FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2024
AND duration < 60;
-- There were also many (9)

-- Check the airports in the city to see which one has the earliest flight to outside the city later
SELECT *
FROM airports
WHERE city = 'Fiftyville';
-- CSF, Fiftyville Regional Airport (8)

-- Check flights to see the earliest one
SELECT *
FROM flights
WHERE day = 29 AND month = 7 AND year = 2024
AND origin_airport_id = 8;
-- The earliest flight is of ID 36, to airport ID 4 at 8:20 AM

-- Find out the town they are going to
SELECT *
FROM airports
WHERE id = 4;
-- New York

-- Check the passengers in the flight
SELECT *
FROM passengers
WHERE flight_id = 36;
-- There were many

-- See if any of these passports are associated with a person that:
-- Left the bakery between 10:15 and 10:25
-- Withdrawals on the Leggett Street ATM before 10:15
-- Made a phone call of less than 60 seconds
-- Etc

-- This query looks for a person that:
-- Has the same passport number as the people who are on the earliest flight of the local airport for the next day (airport->flight->passengers->people)
-- Has the same phone number as the people who made a call with duration below 60 seconds (phone_calls->people)
-- Has the same bank account number as the people who made withdraws on the Leggett Street atm before 10:15 AM (atm_transactions->bank_accounts->people)
-- Has the same license plate as the people who left the bakery in between 10:15 and 10:25 (bakery_security_logs->people)

SELECT p.id
FROM people p, bank_accounts ba, flights f
JOIN bakery_security_logs bsl ON p.license_plate = bsl.license_plate
JOIN atm_transactions atm ON atm.account_number = ba.account_number
JOIN phone_calls pc ON pc.caller = p.phone_number
JOIN airports air ON air.id = f.origin_airport_id
JOIN passengers pass ON pass.flight_id = f.id AND pass.passport_number = p.passport_number
WHERE f.id = 36 AND air.id = 8 AND f.day = 29 AND f.month = 7 AND f.year = 2024
AND pc.day = 28 AND pc.month = 7 AND pc.year = 2024 AND pc.duration < 60
AND ba.person_id = p.id AND atm.year = 2024 AND atm.month = 7 AND atm.day = 28
AND atm.atm_location LIKE '%Leggett Street%' AND atm.transaction_type = 'withdraw'
AND bsl.month = 7 AND bsl.day = 28 AND bsl.year = 2024
AND bsl.hour = 10 AND bsl.minute >= 15 AND bsl.minute <= 25;
-- The only person that matches is Bruce, ID 686048

-- Check who Bruce called on the day with less than 60 seconds
SELECT *
FROM phone_calls
WHERE caller = (SELECT phone_number FROM people WHERE id = 686048)
AND day = 28 AND month = 7 AND year = 2024 AND duration < 60;

-- Receiver is (375) 555-8161
SELECT id, name
FROM people
WHERE phone_number = (
    SELECT *
    FROM phone_calls
    WHERE caller = (SELECT phone_number FROM people WHERE id = 686048)
    AND day = 28 AND month = 7 AND year = 2024 AND duration < 60
    );
-- Receiver is Robin
