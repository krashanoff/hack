module Main (main) where

import System.Environment ( getArgs )

forEach :: Monad m => (t -> m a) -> [t] -> m a
forEach f [h] = f h
forEach f (h:t) = f h >> forEach f t

main :: IO ()
main = do
    args <- getArgs 
    putStrLn "Hey there."
    forEach putStrLn args
