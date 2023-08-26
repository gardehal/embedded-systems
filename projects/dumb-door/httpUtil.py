
class ResponseStatus:
    info = { 1: "INFO" }
    success = { 2: "SUCCESS" }
    redirect = { 3: "REDIRECT" }
    fail = { 4: "FAIL" }
    error = { 5: "ERROR" }

class HttpUtil:
    basicUserHeader = { "User-Agent": "Mozilla/5.0 (Windows NT 6.0; WOW64; rv:24.0) Gecko/20100101 Firefox/24.0" }
    
    def getHtmlHeader(self, code: int, status: str) -> str:
        # TODO, use ResponseStatus?
        
        return f"HTTP/1.0 {code} {status}\r\nContent-type: application/json\r\n\r\n"
    
    def getJsonWrapper(self, code: int, status: str, message: str, data: str) -> str:
        # TODO, use class or obj as wrapper
        
        return f"{{ 'code': {code}, 'status': {status}, 'message': {message}, 'data': {data} }}"
    
    # TODO connecter wifi method
    # TODO setup TCP socket method