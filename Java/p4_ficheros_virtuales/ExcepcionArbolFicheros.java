class ExcepcionArbolFicheros extends Exception {
    public ExcepcionArbolFicheros(String message) {
        super(message);
    }
}

class ParametrosInsuficientesException extends ExcepcionArbolFicheros {
    public ParametrosInsuficientesException(String message) {
        super(message);
    }
}

class ComandoDesconocidoException extends ExcepcionArbolFicheros {
    public ComandoDesconocidoException(String message) {
        super(message);
    }
}

class DirectorioNoEncontradoException extends ExcepcionArbolFicheros {
    public DirectorioNoEncontradoException(String message) {
        super(message);
    }
}

class ArchivoNoEncontradoException extends ExcepcionArbolFicheros {
    public ArchivoNoEncontradoException(String message) {
        super(message);
    }
}

class PermisoDenegadoException extends ExcepcionArbolFicheros {
    public PermisoDenegadoException(String message) {
        super(message);
    }
}

class TamanioExcedidoException extends ExcepcionArbolFicheros {
    public TamanioExcedidoException(String message) {
        super(message);
    }
}

