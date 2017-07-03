namespace T3000.Controls
{
    public interface ISliderControlEvents
    {
        void TopZoneValueChanged(object sender, float newValue);
        void BottomZoneValueChanged(object sender, float newValue);
        void CurrentValueChanged(object sender, float newValue);
        void TopValueChanged(object sender, float newValue);
        void BottomValueChanged(object sender, float newValue);
        void MiddleZoneValueChanged(object sender, float newValue);
        void TopHandleMoved(object sender, float newValue);
        void MiddleHandleMoved(object sender, float newValue);
        void BottomHandleMoved(object sender, float newValue);
    }
}
