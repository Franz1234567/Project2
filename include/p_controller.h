class P_controller{
    public:
        P_controller(double Kp);
        double update(double ref, double actual);
    private:
        double Kp_priv;
};