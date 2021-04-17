from copy import copy
from typing import List


class Solution:
    @staticmethod
    def generateParenthesis(n: int) -> List[str]:
        ret = []
        def generator(to_open, to_close, current_string):
            if to_open == 0 and to_close == 0:
                if current_string:
                    ret.append(current_string)
            open_left = to_open
            close_left = to_close
            string_to_open = current_string
            while open_left:
                string_to_open += "("
                open_left -= 1
                to_close += 1
                generator(open_left, to_close, string_to_open)
            string_to_close = current_string
            while close_left:
                string_to_close += ")"
                close_left -= 1
                generator(to_open, close_left, string_to_close)

        generator(3, 0, "")
        return ret





if __name__ == '__main__':
    print(Solution.generateParenthesis(3))