struct IClock {
    virtual ~IClock() = default;
    virtual float DeltaTime() const = 0;
};

class Services {
    private:
    static inline IClock* clock_ = nullptr;
    
    public:
    static void setClock(IClock* c) { clock_ = c; }
    static IClock& clock() { return *clock_; }
};