-- Lista o nome e id das pessoas
SELECT name, id
FROM people
-- (Relaciona as tabelas people e stars através do id das pessoas)
JOIN stars ON people.id = stars.person_id
-- Que tiverem o movie_id correspondente a algum dos (que atuaram em):
WHERE movie_id IN (
    -- ids dos filmes
    SELECT id
    FROM movies
    -- Que saíram em 2004
    WHERE year = 2004
    )
-- Ordenando-os pelo ano de nascença (menor pro maior)
ORDER BY birth ASC;
