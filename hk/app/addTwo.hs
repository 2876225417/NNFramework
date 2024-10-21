{-# LANGUAGE ForeignFunctionInterface #-}

module MyHaskellModule (sumTwoNumbers) where

import Foreign.C.Types

-- 声明导出给外部使用
foreign export ccall sumTwoNumbers :: CInt -> CInt -> CInt

-- 实际的 Haskell 函数实现
sumTwoNumbers :: CInt -> CInt -> CInt
sumTwoNumbers x y = x + y
