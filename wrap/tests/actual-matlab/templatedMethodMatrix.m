function varargout = templatedMethodMatrix(varargin)
      if length(varargin) == 1 && isa(varargin{1},'matrix const')
        varargout{1} = geometry_wrapper(118, varargin{:});
      else
        error('Arguments do not match any overload of function templatedMethodMatrix');
      end