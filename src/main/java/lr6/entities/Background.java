package lr6.entities;

import org.joml.Vector4f;

public class Background {

    Vector4f background;

    public void setBackground(Vector4f background) {
        this.background = background;
    }

    public Vector4f getBackground() {
        return background;
    }

    public Background(Vector4f background) {
        this.background = background;
    }
}
