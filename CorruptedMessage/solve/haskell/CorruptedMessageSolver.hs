import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified CorruptedMessage (reconstructMessage)

getVars :: TC.Parser (String, Int)
getVars = do s <- TC.spaces >> TC.parseString ; TC.spaces >> TC.next
             k <- TC.spaces >> TC.parseInt
             return (s, k) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (s, k) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ CorruptedMessage.reconstructMessage s k
            hClose hOut
    hClose hIn