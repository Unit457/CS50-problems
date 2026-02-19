-- Lista o título dos filmes
SELECT title
FROM movies
-- (Relaciona as tabelas movies e ratings a partir do movie_id)
JOIN ratings ON movies.id = ratings.movie_id
-- Que tem o id correspondente a algum dos:
WHERE movies.id IN
    (
    -- ids dos filmes
    SELECT id
    FROM movies
    -- (Relaciona as tabelas movies e stars através do movie_id)
    JOIN stars ON movies.id = stars.movie_id
    -- Que tiverem person_id em stars igual a (que estrelaram):
    AND stars.person_id =
        (
        -- id da pessoa
        SELECT id
        FROM people
        -- Que tem nome igual a 'Chadwick Boseman'
        WHERE name = 'Chadwick Boseman'
        )
    )
-- Ordenando-os pela rating (maior pro menor)
ORDER BY rating DESC
-- Limitando em 5 resultados
LIMIT 5;
