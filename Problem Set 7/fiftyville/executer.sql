SELECT id, name
FROM people
WHERE phone_number = (
    SELECT receiver
    FROM phone_calls
    WHERE caller = (SELECT phone_number FROM people WHERE id = 686048)
    AND day = 28 AND month = 7 AND year = 2024 AND duration < 60
    );
