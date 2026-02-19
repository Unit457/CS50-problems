-- Lista os nomes das pessoas
SELECT name
FROM people
-- Que tem o id correspondente a algum dos:
WHERE id IN (
    -- ids das pessoas que estrelaram em filmes
    SELECT person_id
    FROM stars
    -- Que tem movie_id correspondente a algum dos:
    WHERE movie_id IN (
        -- ids dos filmes
        SELECT movie_id
        FROM stars
        -- Que tenham estrelado as pessoas com id correspondente a algum dos:
        WHERE person_id = (
            -- ids das pessoas
            SELECT id
            FROM people
            -- Que tem nome "Kevin Bacon" e nascimento em 1958
            WHERE name = 'Kevin Bacon' AND birth = '1958'
        )
    )
    -- Excluindo o id do Kevin Bacon dos resultados
    AND person_id <> (
            SELECT id
            FROM people
            WHERE name = 'Kevin Bacon' AND birth = '1958'
    )
)
