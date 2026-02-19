-- Lista o nome das pessoas
SELECT name
FROM people
-- (Relaciona as tabelas people e directors através do id das pessoas)
JOIN directors ON people.id = directors.person_id
-- Que tiverem o movie_id correspondente a algum dos (que são diretores de):
WHERE directors.movie_id IN (
    -- ids dos filmes
    SELECT id
    FROM movies
    -- (Relaciona as tabelas movies e ratings através do id dos filmes)
    JOIN ratings ON movies.id = ratings.movie_id
    -- Que tiverem rating igual ou acima de 9
    WHERE ratings.rating >= 9
    );
