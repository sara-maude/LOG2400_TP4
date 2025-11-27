class DecorateurTexture {
public:
    virtual char getTexture() const = 0;
    virtual ~DecorateurTexture() = default;
};

class TextureO : public DecorateurTexture {
public:
    char getTexture() const override { return 'o'; }
};

class TextureHash : public DecorateurTexture {
public:
    char getTexture() const override { return '#'; }
};

class TextureDollar : public DecorateurTexture {
public:
    char getTexture() const override { return '$'; }
};

class TextureStar : public DecorateurTexture {
public:
    char getTexture() const override { return '*'; }
};