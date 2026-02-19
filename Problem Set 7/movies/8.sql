-- Lista o nome das pessoas
SELECT name
FROM people
-- (Relaciona as tabelas people e stars através do id das pessoas)
JOIN stars ON people.id = stars.person_id
-- Que tiverem movie_id correspondente ao (que atuaram em):
WHERE stars.movie_id = (
    -- id do filme
    SELECT id
    FROM movies
    -- Que tenha título igual a 'Toy Story'
    WHERE title = 'Toy Story'
    );
