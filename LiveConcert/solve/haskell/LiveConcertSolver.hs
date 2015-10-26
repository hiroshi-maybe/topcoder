import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified LiveConcert (maxHappiness)

getVars :: TC.Parser ([Int], [String])
getVars = do h <- TC.spaces >> (TC.parseList TC.parseInt) ; TC.spaces >> TC.next
             s <- TC.spaces >> (TC.parseList TC.parseString)
             return (h, s) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (h, s) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ LiveConcert.maxHappiness h s
            hClose hOut
    hClose hIn